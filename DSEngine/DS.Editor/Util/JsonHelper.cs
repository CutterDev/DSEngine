using System;
using System.IO;
using System.Runtime.Serialization;

namespace DS.Editor.Util
{
    public static class SerializeHelper
    {
        public static bool TrySerializeToFile<T>(T obj, string Path, out string errMsg)
        {
            bool result = false;
            errMsg = string.Empty;
            DataContractSerializer serializer = new DataContractSerializer(typeof(T));

            try
            {
                if (!File.Exists(Path))
                {
                    using (FileStream fs = File.Create(Path))
                    {
                        serializer.WriteObject(fs, obj);

                        result = true;
                    }
                }
            }
            catch(Exception e)
            {
                // Log somehow
                errMsg = $"Error Serializing File {e.Message}";
            }

            return result;
        }
    }
}
