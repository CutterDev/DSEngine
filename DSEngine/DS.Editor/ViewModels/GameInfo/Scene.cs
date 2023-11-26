using System.Runtime.Serialization;

namespace DS.Editor.ViewModels;

[DataContract]
public class Scene : BaseViewModel
{
    private string _name;

    [DataMember]
    public string Name
    {
        get { return _name; }
        set
        {
            if (_name != value)
            {
                _name = value;
                OnPropertyChanged(nameof(Name));
            }
        }
    }

    [DataMember]
    public Project Project { get; private set; }

    public Scene(Project project, string name)
    {
        Name = name;
        Project = project;
    }
}
