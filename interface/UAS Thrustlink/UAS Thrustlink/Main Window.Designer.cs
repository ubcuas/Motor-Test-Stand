namespace UAS_Thrustlink
{
    partial class Thrustlink
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.portComboBox = new System.Windows.Forms.ComboBox();
            this.portRefreshButton = new System.Windows.Forms.Button();
            this.connectionButton = new System.Windows.Forms.Button();
            this.statusLabel = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Interval = 20;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(11, 277);
            this.richTextBox1.Margin = new System.Windows.Forms.Padding(2);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(712, 178);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(11, 11);
            this.portComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(66, 21);
            this.portComboBox.TabIndex = 1;
            // 
            // portRefreshButton
            // 
            this.portRefreshButton.Location = new System.Drawing.Point(82, 9);
            this.portRefreshButton.Name = "portRefreshButton";
            this.portRefreshButton.Size = new System.Drawing.Size(75, 23);
            this.portRefreshButton.TabIndex = 3;
            this.portRefreshButton.Text = "Refresh";
            this.portRefreshButton.UseVisualStyleBackColor = true;
            this.portRefreshButton.Click += new System.EventHandler(this.portRefreshButton_Click);
            // 
            // connectionButton
            // 
            this.connectionButton.Location = new System.Drawing.Point(163, 9);
            this.connectionButton.Name = "connectionButton";
            this.connectionButton.Size = new System.Drawing.Size(75, 23);
            this.connectionButton.TabIndex = 4;
            this.connectionButton.Text = "Connect";
            this.connectionButton.UseVisualStyleBackColor = true;
            this.connectionButton.Click += new System.EventHandler(this.connectionButton_Click);
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.ForeColor = System.Drawing.Color.Red;
            this.statusLabel.Location = new System.Drawing.Point(244, 14);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(73, 13);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Disconnected";
            // 
            // textBox1
            // 
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(11, 252);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(712, 20);
            this.textBox1.TabIndex = 6;
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // Thrustlink
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(872, 466);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.statusLabel);
            this.Controls.Add(this.connectionButton);
            this.Controls.Add(this.portRefreshButton);
            this.Controls.Add(this.portComboBox);
            this.Controls.Add(this.richTextBox1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Thrustlink";
            this.Text = "UAS Thrustlink";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.ComboBox portComboBox;
        private System.Windows.Forms.Button portRefreshButton;
        private System.Windows.Forms.Button connectionButton;
        private System.Windows.Forms.Label statusLabel;
        private System.Windows.Forms.TextBox textBox1;
    }
}

