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
using System.IO;
using System.Runtime.CompilerServices;

namespace Thrust_Stand_Interface
{
    public partial class Form1 : Form
    {
        private ulong time = 0;
        private double[] datas = { 0, 0, 0, 0, 0, 0, 0 };
        private char[] delimiters = { ',', ' ', '\t' };
        private string incoming;
        private int baud;
        private int value = 1000;
        private bool isRunning = false;

        delegate void SetTextCallback(string text);

        public Form1()
        {
            InitializeComponent();
            refreshAvailablePorts();
        }

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (textBox1.InvokeRequired)
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
            portSelect.Items.Clear();
            portSelect.Items.AddRange(ports);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;

            if (serialPort1.IsOpen)
            {
                serialPort1.Write("S");
                startStopButton.Text = "Start";
                if (serialPort1.IsOpen) serialPort1.Close();
                isRunning = false;

                label2.Text = "Disconnected";
                label2.ForeColor = Color.Red;
                button1.Text = "Connect";
                refreshAvailablePorts();
                portSelect.Enabled = true;
                baudRateSelect.Enabled = true;
            }
            else
            {
                if (portSelect.Text.Length == 0)
                {
                    string message = "No port selected";
                    string caption = "Incomplete Parameter";
                    MessageBox.Show(message, caption, MessageBoxButtons.OK, MessageBoxIcon.Warning);

                    button1.Enabled = true;
                    return;
                }
                if (!int.TryParse(baudRateSelect.Text, out baud) || baud <= 0)
                {
                    string message = "Invalid baud rate selected";
                    string caption = "Incomplete Parameter";
                    MessageBox.Show(message, caption, MessageBoxButtons.OK, MessageBoxIcon.Warning);

                    button1.Enabled = true;
                    return;
                }

                try
                {
                    serialPort1.PortName = portSelect.Text;
                    serialPort1.BaudRate = baud;
                    serialPort1.Open();
                }
                catch
                {
                    serialPort1.Close();

                    string message = "Cannot open port " + serialPort1.PortName;
                    string caption = "Error opening port";
                    MessageBox.Show(message, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);

                    portSelect.Enabled = true;
                    baudRateSelect.Enabled = true;
                }

                if (serialPort1.IsOpen)
                {
                    trackBar1.Value = 1000;
                    lowerLimitNumeric.Value = 1000;
                    upperLimitNumeric.Value = 2000;
                    sliderValueLabel.Text = "1000";

                    label2.Text = "Connected";
                    label2.ForeColor = Color.Green;
                    button1.Text = "Disconnect";
                    portSelect.Enabled = false;
                    baudRateSelect.Enabled = false;
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
            catch //(Exception ex)
            {
                //MessageBox.Show(Convert.ToString(ex));
                if (serialPort1.IsOpen) serialPort1.Close();
            }
        }

        private void serialSend_Click(object sender, EventArgs e)
        {
            string outcoming = textBox1.Text;
            textBox1.Clear();
            if (serialPort1.IsOpen) serialPort1.Write(outcoming);
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 6; i++)
            {
                datas[i] = 0;
                chart1.Series[i].Points.Clear();
            }
            richTextBox1.Clear();
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

        private void exportButton_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
            //MessageBox.Show(Convert.ToString(saveFileDialog1.FileName));
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            string path = saveFileDialog1.FileName;
            using (StreamWriter sw = File.CreateText(path))
            {
                sw.WriteLine(richTextBox1.Text);
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            value = trackBar1.Value;
            sliderValueLabel.Text = Convert.ToString(value);
            if (serialPort1.IsOpen)
            {
                string outWrite = "P" + value;
                serialPort1.Write(outWrite);
            }
        }

        private void calibrateButton_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("C");
                //serialPort1.DiscardInBuffer();
            }
        }

        private void lowerLimitNumeric_ValueChanged(object sender, EventArgs e)
        {
            trackBar1.Minimum = Convert.ToInt32(lowerLimitNumeric.Value);
            if (trackBar1.Value < Convert.ToInt32(lowerLimitNumeric.Value)) trackBar1.Value = Convert.ToInt32(lowerLimitNumeric.Value);
        }

        private void upperLimitNumeric_ValueChanged(object sender, EventArgs e)
        {
            trackBar1.Maximum = Convert.ToInt32(upperLimitNumeric.Value);
            if (trackBar1.Value > Convert.ToInt32(upperLimitNumeric.Value)) trackBar1.Value = Convert.ToInt32(upperLimitNumeric.Value);
        }

        private void startStopButton_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (isRunning)
                {
                    serialPort1.Write("S");
                    startStopButton.Text = "Start";
                }
                else
                {
                    serialPort1.Write("R");
                    startStopButton.Text = "Stop";
                }
                isRunning = !isRunning;
            }
        }

        private void aboutButton_Click(object sender, EventArgs e)
        {
            string title = "About";
            string content = "UBC UAS Thrust Stand Interface\nCharles Surianto\nDecember 2022";
            MessageBox.Show(content, title, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
