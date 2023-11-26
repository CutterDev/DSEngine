using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace DS.Editor.ViewModels;

[DataContract(Name = "Game")]
public class Project : BaseViewModel
{
    private string extension = ".dsproject";

    [DataMember]
    public string Name { get; private set; }

    [DataMember]
    public string BasePath { get; private set; }

    [DataMember(Name = "Scenes")]
    private ObservableCollection<Scene> _scenes = new ObservableCollection<Scene>();

    public ReadOnlyObservableCollection<Scene> Scenes { get; }

    public Project(string name, string path)
    {
        Name = name;
        BasePath = Path.Combine(path, $"{Name}{extension}");
        _scenes.Add(new Scene(this, "DemoScene"));
    }
}
