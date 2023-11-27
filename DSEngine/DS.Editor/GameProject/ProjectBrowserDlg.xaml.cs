using DS.Editor.Util;
using DS.Editor.ViewModels;
using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace DS.Editor.GameProject
{
    /// <summary>
    /// Interaction logic for ProjectBrowserDlg.xaml
    /// </summary>
    public partial class ProjectBrowserDlg : Window
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public ProjectBrowserDlg()
        {
            InitializeComponent();

            Initialize();
        }

        /// <summary>
        /// Get the default Directory that has the existing Projects. 
        /// </summary>
        // TODO Add a file that holds all recently open Projects aswell.
        private void Initialize()
        {
            OpenProject dataCtx = this.DataContext as OpenProject;

            try
            {
                if (Directory.Exists(ProgramConstants.ProjectsDirectory))
                {
                    // Potential Project directories need to check for project file
                    string[] projDirs = Directory.GetDirectories(ProgramConstants.ProjectsDirectory);

                    for (int i = 0; i < projDirs.Length; i++)
                    {
                        string proj = projDirs[i];
                        string[] projFiles = Directory.GetFiles(proj);

                        for (int x = 0; x < projFiles.Length; x++)
                        {
                            string file = projFiles[x];

                            if (file.EndsWith(ProgramConstants.ProjectExtension))
                            {
                                if (SerializeHelper.TryDeserializeFromFile<Project>(file, out Project project, out string errMsg))
                                {
                                    dataCtx.ExistingProjects.Add(project);
                                }
                                else
                                {
                                    WpfHelper.ShowError(errMsg);
                                }
                            }
                        }
                    }
                }
            }
            catch(Exception e)
            {
                WpfHelper.ShowError($"Error loading Existing Projects {e.Message}");
            }
        }

        /// <summary>
        /// Selected Changed Event when a different List item (Existing project) is selected.
        /// </summary>
        private void ExistingProject_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (lbProjects.SelectedItem != null)
            {
                Project selectedProject = lbProjects.SelectedItem as Project;

                if (selectedProject != null)
                {
                    OpenProject dataCtx = this.DataContext as OpenProject;

                    dataCtx.SelectedProjectPath = selectedProject.BasePath;
                }
            }
        }

        private void OpenProject_Click(object sender, RoutedEventArgs e)
        {
            OpenProject();
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

        /// <summary>
        /// Check if the given <paramref name="filePath"/> exists then close the dialog if it does.
        /// </summary>
        private void OpenProject()
        {
            OpenProject dataCtx = this.DataContext as OpenProject;

            if (File.Exists(dataCtx.SelectedProjectPath))
            {
                DialogResult = true;
                this.Close();
            }
            else
            {
                WpfHelper.ShowError("Project does not exist.");
            }
        }

        /// <summary>
        /// Create a new Project file and the directory
        /// </summary>
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
                WpfHelper.ShowError($"Error Creating Project {ex.Message}");
            }

            Project newProject = new Project(project.Name, project.FilePath);

            if (SerializeHelper.TrySerializeToFile<Project>(newProject, newProject.BasePath, out string errmsg))
            {
                OpenProject();
            }
            else
            {
                WpfHelper.ShowError(errmsg);
            }
        }
    }
}
