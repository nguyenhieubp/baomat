using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace AppChatBaoMat
{
    public class DesEncryption
    {
        private const string DefaultKey = "hihihihi"; // Key mặc định

        public static string Encrypt(string clearText, string key = null)
        {
            byte[] clearBytes = Encoding.Unicode.GetBytes(clearText);
            using (DESCryptoServiceProvider des = new DESCryptoServiceProvider())
            {
                byte[] keyBytes = GetKeyBytes(key); // Sử dụng key truyền vào hoặc key mặc định
                Console.WriteLine(keyBytes);
                des.Key = keyBytes;
                des.IV = keyBytes;
                using (MemoryStream ms = new MemoryStream())
                {
                    using (CryptoStream cs = new CryptoStream(ms, des.CreateEncryptor(), CryptoStreamMode.Write))
                    {
                        cs.Write(clearBytes, 0, clearBytes.Length);
                        cs.Close();
                    }
                    return Convert.ToBase64String(ms.ToArray());
                }
            }
        }

        public static string Decrypt(string cipherText, string key = null)
        {
            byte[] cipherBytes = Convert.FromBase64String(cipherText);
            using (DESCryptoServiceProvider des = new DESCryptoServiceProvider())
            {
                byte[] keyBytes = GetKeyBytes(key); // Sử dụng key truyền vào hoặc key mặc định
                des.Key = keyBytes;
                des.IV = keyBytes;
                using (MemoryStream ms = new MemoryStream())
                {
                    using (CryptoStream cs = new CryptoStream(ms, des.CreateDecryptor(), CryptoStreamMode.Write))
                    {
                        cs.Write(cipherBytes, 0, cipherBytes.Length);
                        cs.Close();
                    }
                    return Encoding.Unicode.GetString(ms.ToArray());
                }
            }
        }

        private static byte[] GetKeyBytes(string key)
        {
            if (string.IsNullOrEmpty(key))
            {
                // Sử dụng key mặc định nếu không có key được truyền vào
                return Encoding.ASCII.GetBytes(DefaultKey.Substring(0, 8));
            }
            else
            {
                // Sử dụng key được truyền vào
                return Encoding.ASCII.GetBytes(key.Substring(0, 8));
            }
        }
    }
}
