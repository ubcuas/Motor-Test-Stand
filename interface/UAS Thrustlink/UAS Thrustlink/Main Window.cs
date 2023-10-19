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

namespace UAS_Thrustlink
{
    public partial class Thrustlink : Form
    {
        public Thrustlink()
        {
            InitializeComponent();
        }

        private void updateVisuals()
        {
            if (serialPort1.IsOpen)
            {
                connectionButton.Text = "Disconnect";
                portComboBox.Enabled = false;
                statusLabel.Text = "Connected";
                statusLabel.ForeColor = Color.Green;
                textBox1.Enabled = true;
                dashboardGroupBox.Enabled = true;
            }
            else
            {
                connectionButton.Text = "Connect";
                portComboBox.Enabled = true;
                statusLabel.Text = "Disconnected";
                statusLabel.ForeColor = Color.Red;
                textBox1.Enabled = false;
                dashboardGroupBox.Enabled = false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // send pulse value to controller periodically
            // also check if the serial port is disconnected or no
            try
            {
                serialPort1.Write("");
            }
            catch (Exception ex)
            {
                serialPort1.Close();
                updateVisuals();

                timer1.Enabled = false;
            }
        }

        private void portRefreshButton_Click(object sender, EventArgs e)
        {
            // refresh available serial ports
            string[] availablePorts = SerialPort.GetPortNames();
            portComboBox.Items.Clear();
            portComboBox.Items.AddRange(availablePorts);

            if (portComboBox.Text == "" && portComboBox.Items.Count > 0)
            {
                try
                {
                    portComboBox.SelectedIndex = 0;
                }
                catch (Exception ex)
                {
                    richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + ex.Message + "\n");
                }
            }
        }

        private void connectionButton_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    // close the connection
                    serialPort1.Close();
                }
                catch (Exception ex)
                {
                    richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + ex.Message + "\n");
                }
            }
            else
            {
                try
                {
                    // establish the connection
                    serialPort1.PortName = portComboBox.Text;
                    serialPort1.Open();
                }
                catch (Exception ex)
                {
                    richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + ex.Message + "\n");
                }
                timer1.Enabled = true;
            }
            updateVisuals();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            // set the current caret position to the end
            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            // scroll it automatically
            richTextBox1.ScrollToCaret();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r') // pressed enter
            {
                try
                {
                    serialPort1.Write(textBox1.Text + "\n");
                }
                catch (Exception ex)
                {
                    richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + ex.Message + "\n");
                    serialPort1.Close();
                    updateVisuals();
                }
                textBox1.Clear();
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + serialPort1.ReadLine() + "\n");
            }
            catch (Exception ex)
            {
                richTextBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:fff") + " " + ex.Message + "\n");
            }
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            var confirmResult = MessageBox.Show(
                "Clear the terminal?",
                "",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Warning,
                MessageBoxDefaultButton.Button2);
            if (confirmResult == DialogResult.Yes)
            {
                richTextBox1.Clear();
            }
        }

        private void infoButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "UAS Thrustlink\n\nCharles Surianto\nOctober 2023",
                "",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information);
        }
    }
}
