using DS.Editor.Util;
using DS.Editor.ViewModels;
using System;
using System.Collections.Generic;
using System.IO;
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
                    CreateProject(project);
                }
            }
        }

        private void CreateProject(NewProject project)
        {
            try
            {
                if (!Directory.Exists(project.FilePath))
                {
                    Directory.CreateDirectory(project.FilePath);

                    // Hard Coded Template Folders for user
                    Directory.CreateDirectory(System.IO.Path.Combine(project.FilePath, "Scenes"));
                    Directory.CreateDirectory(System.IO.Path.Combine(project.FilePath, "Textures"));
                    Directory.CreateDirectory(System.IO.Path.Combine(project.FilePath, "Meshes"));
                    Directory.CreateDirectory(System.IO.Path.Combine(project.FilePath, "Shaders"));
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            Project newProject = new Project(project.Name, project.FilePath);

            if (SerializeHelper.TrySerializeToFile<Project>(newProject, newProject.BasePath, out string errmsg))
            {

            }
            else
            {
                if (!string.IsNullOrWhiteSpace(errmsg))
                {
                    MessageBox.Show(errmsg, "Error");
                }
            }
        }
    }
}
