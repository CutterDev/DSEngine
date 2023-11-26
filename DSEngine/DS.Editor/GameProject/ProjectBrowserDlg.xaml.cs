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
using System.Windows.Shapes;

namespace DS.Editor.GameProject
{
    /// <summary>
    /// Interaction logic for ProjectBrowserDlg.xaml
    /// </summary>
    public partial class ProjectBrowserDlg : Window
    {
        public ProjectBrowserDlg()
        {
            InitializeComponent();
            this.Owner = App.Current.MainWindow;
        }

        private void OpenProject_Click(object sender, RoutedEventArgs e)
        {

        }

        private void NewProject_Click(object sender, RoutedEventArgs e)
        {
            NewProjectDlg newProjectDlg = new NewProjectDlg();

            if (newProjectDlg.ShowDialog().Value)
            {
                if (newProjectDlg.GetModel(out NewProject project))
                {

                }
            }
        }
    }
}
