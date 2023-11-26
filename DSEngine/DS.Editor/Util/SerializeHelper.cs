using System;
using System.IO;
using System.Runtime.Serialization;

namespace DS.Editor.Util
{
    public static class SerializeHelper
    {
        public static bool TrySerializeToFile<T>(T obj, string path, out string errMsg)
        {
            bool result = false;
            errMsg = string.Empty;
            DataContractSerializer serializer = new DataContractSerializer(typeof(T));

            try
            {
                if (!File.Exists(path))
                {
                    using (FileStream fs = File.Create(path))
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

        public static bool TryDeserializeFromFile<T>(string path, out T project, out string errMsg)
        {
            bool result = false;
            project = default;
            errMsg = string.Empty;
            DataContractSerializer serializer = new DataContractSerializer(typeof(T));

            try
            {
                if (File.Exists(path))
                {
                    using (FileStream fs = new FileStream(path, FileMode.Open))
                    {

                        project = (T)serializer.ReadObject(fs);
                        result = true;
                    }
                }
            }
            catch (Exception e)
            {
                // Log somehow
                errMsg = $"Error Serializing File {e.Message}";
            }

            return result;
        }
    }
}
