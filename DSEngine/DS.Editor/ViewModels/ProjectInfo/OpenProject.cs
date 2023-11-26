using System.Collections.ObjectModel;

namespace DS.Editor.ViewModels
{
    public class OpenProject : BaseViewModel
    {
        public string SelectedProjectPath { get; set; }

        public ObservableCollection<Project> ExistingProjects { get; private set; }

        public OpenProject()
        {
            ExistingProjects = new ObservableCollection<Project>();
        }
    }
}
