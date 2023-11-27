using System.Collections.ObjectModel;

namespace DS.Editor.ViewModels
{
    public class OpenProject : BaseViewModel
    {
        private string _selectedProjectPath;
        public string SelectedProjectPath
        {
            get { return _selectedProjectPath; }
            set
            {
                if (_selectedProjectPath != value)
                {
                    _selectedProjectPath = value;
                    OnPropertyChanged(nameof(SelectedProjectPath));
                }
            }
        }

        public ObservableCollection<Project> ExistingProjects { get; private set; }

        public OpenProject()
        {
            ExistingProjects = new ObservableCollection<Project>();
        }
    }
}
