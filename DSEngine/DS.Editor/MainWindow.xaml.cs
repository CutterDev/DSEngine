using DS.Editor.GameProject;
using DS.Editor.Util;
using DS.Editor.ViewModels;
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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DS.Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Project OpenProject { get; set; }
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            OpenBrowserDialog();
        }

        private void OpenBrowserDialog()
        {
            ProjectBrowserDlg projectBrowser = new ProjectBrowserDlg();

            if (projectBrowser.ShowDialog().Value)
            {
                OpenProject openProject = projectBrowser.DataContext as OpenProject;

                string errMsg = string.Empty;
                if (openProject != null && ProjectFileHelper.IsValidProjectFile(openProject.SelectedProjectPath, out errMsg))
                {
                    Project project;
                    if (SerializeHelper.TryDeserializeFromFile(openProject.SelectedProjectPath, out project, out errMsg))
                    {
                        OpenProject = project;
                    }
                }
                
                if (!string.IsNullOrWhiteSpace(errMsg))
                {
                    WpfHelper.ShowError(errMsg);
                }
            }
            else
            {
                Application.Current.Shutdown();
            }
        }
    }
}
