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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Thrustlink));
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.portComboBox = new System.Windows.Forms.ComboBox();
            this.portRefreshButton = new System.Windows.Forms.Button();
            this.connectionButton = new System.Windows.Forms.Button();
            this.statusLabel = new System.Windows.Forms.Label();
            this.serialTextBox = new System.Windows.Forms.TextBox();
            this.infoButton = new System.Windows.Forms.Button();
            this.serialConnectionGroupBox = new System.Windows.Forms.GroupBox();
            this.dashboardGroupBox = new System.Windows.Forms.GroupBox();
            this.pulseTrackBar = new System.Windows.Forms.TrackBar();
            this.clearButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.pulseNumericBox = new System.Windows.Forms.NumericUpDown();
            this.signalLabel = new System.Windows.Forms.Label();
            this.serialConnectionGroupBox.SuspendLayout();
            this.dashboardGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pulseTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pulseNumericBox)).BeginInit();
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
            this.richTextBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBox1.Location = new System.Drawing.Point(12, 306);
            this.richTextBox1.Margin = new System.Windows.Forms.Padding(2);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(780, 244);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(15, 21);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(66, 21);
            this.portComboBox.TabIndex = 1;
            // 
            // portRefreshButton
            // 
            this.portRefreshButton.Location = new System.Drawing.Point(87, 19);
            this.portRefreshButton.Name = "portRefreshButton";
            this.portRefreshButton.Size = new System.Drawing.Size(75, 23);
            this.portRefreshButton.TabIndex = 3;
            this.portRefreshButton.Text = "Refresh";
            this.portRefreshButton.UseVisualStyleBackColor = true;
            this.portRefreshButton.Click += new System.EventHandler(this.portRefreshButton_Click);
            // 
            // connectionButton
            // 
            this.connectionButton.Location = new System.Drawing.Point(168, 19);
            this.connectionButton.Name = "connectionButton";
            this.connectionButton.Size = new System.Drawing.Size(75, 23);
            this.connectionButton.TabIndex = 4;
            this.connectionButton.Text = "Connect";
            this.connectionButton.UseVisualStyleBackColor = true;
            this.connectionButton.Click += new System.EventHandler(this.connectionButton_Click);
            // 
            // statusLabel
            // 
            this.statusLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusLabel.AutoSize = true;
            this.statusLabel.ForeColor = System.Drawing.Color.Red;
            this.statusLabel.Location = new System.Drawing.Point(249, 24);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(73, 13);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Disconnected";
            this.statusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // serialTextBox
            // 
            this.serialTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.serialTextBox.Enabled = false;
            this.serialTextBox.Location = new System.Drawing.Point(12, 280);
            this.serialTextBox.Name = "serialTextBox";
            this.serialTextBox.Size = new System.Drawing.Size(860, 20);
            this.serialTextBox.TabIndex = 6;
            this.serialTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.serialTextBox_KeyPress);
            // 
            // infoButton
            // 
            this.infoButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.infoButton.Location = new System.Drawing.Point(797, 527);
            this.infoButton.Name = "infoButton";
            this.infoButton.Size = new System.Drawing.Size(75, 23);
            this.infoButton.TabIndex = 7;
            this.infoButton.Text = "Info";
            this.infoButton.UseVisualStyleBackColor = true;
            this.infoButton.Click += new System.EventHandler(this.infoButton_Click);
            // 
            // serialConnectionGroupBox
            // 
            this.serialConnectionGroupBox.Controls.Add(this.portComboBox);
            this.serialConnectionGroupBox.Controls.Add(this.portRefreshButton);
            this.serialConnectionGroupBox.Controls.Add(this.connectionButton);
            this.serialConnectionGroupBox.Controls.Add(this.statusLabel);
            this.serialConnectionGroupBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.serialConnectionGroupBox.Location = new System.Drawing.Point(12, 12);
            this.serialConnectionGroupBox.Name = "serialConnectionGroupBox";
            this.serialConnectionGroupBox.Size = new System.Drawing.Size(335, 56);
            this.serialConnectionGroupBox.TabIndex = 8;
            this.serialConnectionGroupBox.TabStop = false;
            this.serialConnectionGroupBox.Text = "Serial Connection";
            // 
            // dashboardGroupBox
            // 
            this.dashboardGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dashboardGroupBox.Controls.Add(this.signalLabel);
            this.dashboardGroupBox.Controls.Add(this.pulseNumericBox);
            this.dashboardGroupBox.Controls.Add(this.pulseTrackBar);
            this.dashboardGroupBox.Location = new System.Drawing.Point(12, 74);
            this.dashboardGroupBox.Name = "dashboardGroupBox";
            this.dashboardGroupBox.Size = new System.Drawing.Size(860, 200);
            this.dashboardGroupBox.TabIndex = 9;
            this.dashboardGroupBox.TabStop = false;
            this.dashboardGroupBox.Text = "Dashboard";
            // 
            // pulseTrackBar
            // 
            this.pulseTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pulseTrackBar.LargeChange = 100;
            this.pulseTrackBar.Location = new System.Drawing.Point(6, 149);
            this.pulseTrackBar.Maximum = 2000;
            this.pulseTrackBar.Minimum = 1000;
            this.pulseTrackBar.Name = "pulseTrackBar";
            this.pulseTrackBar.Size = new System.Drawing.Size(848, 45);
            this.pulseTrackBar.SmallChange = 10;
            this.pulseTrackBar.TabIndex = 0;
            this.pulseTrackBar.TabStop = false;
            this.pulseTrackBar.TickFrequency = 10;
            this.pulseTrackBar.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.pulseTrackBar.Value = 1000;
            this.pulseTrackBar.ValueChanged += new System.EventHandler(this.pulseTrackBar_ValueChanged);
            // 
            // clearButton
            // 
            this.clearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.clearButton.Location = new System.Drawing.Point(797, 306);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(75, 23);
            this.clearButton.TabIndex = 10;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.Location = new System.Drawing.Point(797, 335);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 11;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            // 
            // pulseNumericBox
            // 
            this.pulseNumericBox.Location = new System.Drawing.Point(57, 123);
            this.pulseNumericBox.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.pulseNumericBox.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.pulseNumericBox.Name = "pulseNumericBox";
            this.pulseNumericBox.Size = new System.Drawing.Size(51, 20);
            this.pulseNumericBox.TabIndex = 1;
            this.pulseNumericBox.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.pulseNumericBox.ValueChanged += new System.EventHandler(this.pulseNumericBox_ValueChanged);
            // 
            // signalLabel
            // 
            this.signalLabel.AutoSize = true;
            this.signalLabel.Location = new System.Drawing.Point(12, 125);
            this.signalLabel.Name = "signalLabel";
            this.signalLabel.Size = new System.Drawing.Size(39, 13);
            this.signalLabel.TabIndex = 2;
            this.signalLabel.Text = "Signal:";
            // 
            // Thrustlink
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(884, 561);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.dashboardGroupBox);
            this.Controls.Add(this.serialConnectionGroupBox);
            this.Controls.Add(this.infoButton);
            this.Controls.Add(this.serialTextBox);
            this.Controls.Add(this.richTextBox1);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(900, 600);
            this.Name = "Thrustlink";
            this.Text = "UAS Thrustlink";
            this.serialConnectionGroupBox.ResumeLayout(false);
            this.serialConnectionGroupBox.PerformLayout();
            this.dashboardGroupBox.ResumeLayout(false);
            this.dashboardGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pulseTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pulseNumericBox)).EndInit();
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
        private System.Windows.Forms.TextBox serialTextBox;
        private System.Windows.Forms.Button infoButton;
        private System.Windows.Forms.GroupBox serialConnectionGroupBox;
        private System.Windows.Forms.GroupBox dashboardGroupBox;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.TrackBar pulseTrackBar;
        private System.Windows.Forms.NumericUpDown pulseNumericBox;
        private System.Windows.Forms.Label signalLabel;
    }
}

