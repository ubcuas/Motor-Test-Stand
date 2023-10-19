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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.infoButton = new System.Windows.Forms.Button();
            this.serialConnectionGroupBox = new System.Windows.Forms.GroupBox();
            this.dashboardGroupBox = new System.Windows.Forms.GroupBox();
            this.clearButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.serialConnectionGroupBox.SuspendLayout();
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
            this.richTextBox1.Location = new System.Drawing.Point(18, 471);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(1168, 373);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(22, 29);
            this.portComboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(97, 28);
            this.portComboBox.TabIndex = 1;
            // 
            // portRefreshButton
            // 
            this.portRefreshButton.Location = new System.Drawing.Point(130, 29);
            this.portRefreshButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.portRefreshButton.Name = "portRefreshButton";
            this.portRefreshButton.Size = new System.Drawing.Size(112, 35);
            this.portRefreshButton.TabIndex = 3;
            this.portRefreshButton.Text = "Refresh";
            this.portRefreshButton.UseVisualStyleBackColor = true;
            this.portRefreshButton.Click += new System.EventHandler(this.portRefreshButton_Click);
            // 
            // connectionButton
            // 
            this.connectionButton.Location = new System.Drawing.Point(252, 29);
            this.connectionButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.connectionButton.Name = "connectionButton";
            this.connectionButton.Size = new System.Drawing.Size(112, 35);
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
            this.statusLabel.Location = new System.Drawing.Point(374, 37);
            this.statusLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(107, 20);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "Disconnected";
            this.statusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(18, 431);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(1288, 26);
            this.textBox1.TabIndex = 6;
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // infoButton
            // 
            this.infoButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.infoButton.Location = new System.Drawing.Point(1196, 811);
            this.infoButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.infoButton.Name = "infoButton";
            this.infoButton.Size = new System.Drawing.Size(112, 35);
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
            this.serialConnectionGroupBox.Location = new System.Drawing.Point(18, 18);
            this.serialConnectionGroupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.serialConnectionGroupBox.Name = "serialConnectionGroupBox";
            this.serialConnectionGroupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.serialConnectionGroupBox.Size = new System.Drawing.Size(502, 86);
            this.serialConnectionGroupBox.TabIndex = 8;
            this.serialConnectionGroupBox.TabStop = false;
            this.serialConnectionGroupBox.Text = "Serial Connection";
            // 
            // dashboardGroupBox
            // 
            this.dashboardGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dashboardGroupBox.Enabled = false;
            this.dashboardGroupBox.Location = new System.Drawing.Point(18, 114);
            this.dashboardGroupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.dashboardGroupBox.Name = "dashboardGroupBox";
            this.dashboardGroupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.dashboardGroupBox.Size = new System.Drawing.Size(1290, 308);
            this.dashboardGroupBox.TabIndex = 9;
            this.dashboardGroupBox.TabStop = false;
            this.dashboardGroupBox.Text = "Dashboard";
            // 
            // clearButton
            // 
            this.clearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.clearButton.Location = new System.Drawing.Point(1196, 471);
            this.clearButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(112, 35);
            this.clearButton.TabIndex = 10;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.Location = new System.Drawing.Point(1196, 515);
            this.saveButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(112, 35);
            this.saveButton.TabIndex = 11;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            // 
            // Thrustlink
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1326, 863);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.dashboardGroupBox);
            this.Controls.Add(this.serialConnectionGroupBox);
            this.Controls.Add(this.infoButton);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.richTextBox1);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(1339, 893);
            this.Name = "Thrustlink";
            this.Text = "UAS Thrustlink";
            this.serialConnectionGroupBox.ResumeLayout(false);
            this.serialConnectionGroupBox.PerformLayout();
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
        private System.Windows.Forms.Button infoButton;
        private System.Windows.Forms.GroupBox serialConnectionGroupBox;
        private System.Windows.Forms.GroupBox dashboardGroupBox;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.Button saveButton;
    }
}

