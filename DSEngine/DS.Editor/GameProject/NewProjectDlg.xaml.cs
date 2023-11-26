﻿using DS.Editor.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace DS.Editor.GameProject
{
    /// <summary>
    /// Interaction logic for NewProjectDlg.xaml
    /// </summary>
    public partial class NewProjectDlg : Window
    {
        public NewProjectDlg()
        {
            InitializeComponent();
            this.Owner = App.Current.MainWindow;
        }

        public bool GetModel(out NewProject project)
        {
            bool result = false;
            project = null;

            if (this.DataContext != null)
            {
                project = this.DataContext as NewProject;

                result = project != null;
            }

            return result;
        }

        private void CreateProject_Click(object sender, RoutedEventArgs e)
        {
            NewProject project = this.DataContext as NewProject;

            string errorMsg;
            if (project.ValidProject(out errorMsg))
            {
                this.DialogResult = true;
                this.Close();
            }
            else
            {
                if (!string.IsNullOrWhiteSpace(errorMsg))
                {
                    MessageBox.Show(errorMsg, "Error");
                }
            }
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
            this.Close();
        }
    }
}
