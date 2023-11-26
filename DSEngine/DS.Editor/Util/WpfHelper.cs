using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DS.Editor.Util
{
    public static class WpfHelper
    {
        public static void ShowError(string message)
        {
            if (!string.IsNullOrWhiteSpace(message))
            {
                MessageBox.Show(message, "Error");
            }
        }
    }
}
