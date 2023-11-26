using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DS.Editor.ViewModels
{
    public class NewProject : BaseViewModel
    {
        private string _name = "New Project";
        private string _filepath;

        public NewProject()
        {
            _filepath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "DS Projects", "Project1");
        }

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

        public string FilePath
        {
            get { return _filepath; }
            set
            {
                if (_filepath != value)
                {
                    _filepath = value;
                    OnPropertyChanged(nameof(FilePath));
                }
            }
        }

        public bool ValidProject(out string errMessage)
        {
            bool result = true;
            errMessage = string.Empty;

            if (string.IsNullOrEmpty(Name))
            {
                result = false;
                errMessage = "Name cannot be Empty";
            }

            if (string.IsNullOrEmpty(_filepath))
            {
                result = false;
                errMessage = "File path cannot be Empty";
            }

            try
            {
                // If Directory exists just invalidate it to not cause any problems.
                if (Directory.Exists(_filepath))
                {
                    result = false;
                    errMessage = "Project Path Already Exists";
                }
            }
            catch(Exception e)
            {
                errMessage = $"Problem creating Project: {e.Message}";
            }

            return result;
        }
    }
}
