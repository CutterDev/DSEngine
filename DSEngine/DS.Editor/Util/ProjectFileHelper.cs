using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DS.Editor.Util
{
    public static class ProjectFileHelper
    {
        /// <summary>
        /// Does not fully validate the Project File Path, and Exists
        /// </summary>
        public static bool IsValidProjectFile(string path, out string errMsg)
        {
            bool result = false;
            errMsg = string.Empty;
            try
            {
                if (!string.IsNullOrWhiteSpace(path) && path.EndsWith(ProgramConstants.ProjectExtension) && File.Exists(path))
                {
                    result = true;
                }
            }
            catch (Exception e)
            {
                errMsg = $"Project is not valid File Error Occured {e.Message}";
            }

            return result;
        }
    }
}
