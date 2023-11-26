using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DS.Editor.Util
{
    public static class ProgramConstants
    {
        /// <summary>
        /// Default Directory for Projectsd
        /// </summary>
        public static string ProjectsDirectory = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "DS Projects");

        public const string ProjectExtension = ".dsproject";
    }
}
