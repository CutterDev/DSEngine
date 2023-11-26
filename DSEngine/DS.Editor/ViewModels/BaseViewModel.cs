using System.ComponentModel;
using System.Runtime.Serialization;

namespace DS.Editor.ViewModels
{
    [DataContract(IsReference = true)]
    public class BaseViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
