using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Linq.Expressions;
using static System.Net.Mime.MediaTypeNames;

namespace Thrust_Stand_Interface
{
    public partial class Form1 : Form
    {
        private bool connected = false;
        private ulong time = 0;
        private double[] datas = { 0, 0, 0, 0, 0, 0, 0 };
        private char[] delimiters = { ',', ' ', '\t' };
        private string incoming;

        delegate void SetTextCallback(string text);

        public Form1()
        {
            InitializeComponent();
            refreshAvailablePorts();
            //chart1.Show();
        }

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                Invoke(d, new object[] { text });
            }
            else
            {
                richTextBox1.AppendText(text);
                string[] dataStrings = incoming.Split(delimiters);
                try
                {
                    time = Convert.ToUInt64(dataStrings[0]);
                }
                catch { }

                for (int i = 0; i < 6; i++)
                {
                    try
                    {
                        datas[i] = Convert.ToDouble(dataStrings[i + 1]);
                    }
                    catch { continue; }
                }
                updateChart();
            }
        }

        void refreshAvailablePorts()
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(ports);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;

            if (comboBox1.Text.Length == 0)
            {
                string message = "No port selected";
                string caption = "Incomplete Parameter";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                MessageBox.Show(message, caption, buttons);

                button1.Enabled = true;
                return;
            }

            if (connected)
            {
                if (serialPort1.IsOpen) serialPort1.Close();
                serialSendButton.Enabled = false;
                textBox1.Enabled = false;
                connected = false;

                label2.Text = "Disconnected";
                label2.ForeColor = Color.Red;
                button1.Text = "Connect";
                refreshAvailablePorts();
                comboBox1.Enabled = true;
            }
            else
            {
                try
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.Open();
                }
                catch
                {
                    serialPort1.Close();

                    string message = "Cannot open port " + serialPort1.PortName;
                    string caption = "Error opening port";
                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show(message, caption, buttons);

                    comboBox1.Enabled = true;
                }

                if (serialPort1.IsOpen)
                {
                    serialSendButton.Enabled = true;
                    textBox1.Enabled = true;
                    connected = true;

                    label2.Text = "Connected";
                    label2.ForeColor = Color.Green;
                    button1.Text = "Disconnect";
                    comboBox1.Enabled = false;
                }
                else
                {
                    refreshAvailablePorts();
                }
            }

            button1.Enabled = true;
        }
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                incoming = serialPort1.ReadLine();
                incoming = serialPort1.ReadLine();
                serialPort1.DiscardInBuffer(); // clear remaining data

                if (incoming != null)
                {
                    //richTextBox1.AppendText(incoming);
                    SetText(incoming);
                }
            }
            catch (Exception ex)
            {
                //MessageBox.Show(Convert.ToString(ex));
                if (serialPort1.IsOpen) serialPort1.Close();
            }
        }

        private void serialSend_Click(object sender, EventArgs e)
        {
            string outcoming = textBox1.Text;
            textBox1.Clear();
            serialPort1.Write(outcoming);
        }

        private void clearTerminalButton_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
            time = 0;
        }

        private void comboBox1_MouseDown(object sender, MouseEventArgs e)
        {
            refreshAvailablePorts();
        }

        private void updateChart()
        {
            for (int i = 0; i < 6; i++)
            {
                chart1.Series[i].Points.AddXY(time, datas[i]);
            }
        }

        private void clearChartButton_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 6; i++)
                chart1.Series[i].Points.Clear();
            time = 0;
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            //MessageBox.Show(Convert.ToString(Convert.ToInt32(e.KeyChar)));
            if (Convert.ToInt32(e.KeyChar) == 13)
            {
                string outcoming = textBox1.Text;
                textBox1.Clear();
                if (serialPort1.IsOpen) serialPort1.Write(outcoming);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            time++;
        }
    }
}
