using AppChatBaoMat.Db;
using AppChatBaoMat.Models;
using Microsoft.AspNetCore.SignalR;

namespace AppChatBaoMat.ChatHub
{
    public class ChatHubRealTime: Hub
    {
        private readonly ChatDb _db;

        public ChatHubRealTime(ChatDb db)
        {
            _db = db;
        }

        public async Task SendMessage(Messages message)
        {
            // Mã hóa User và Text trước khi lưu vào cơ sở dữ liệu
            Messages messageCrypt = new Messages()
            {
                MessageId = message.MessageId,
                Text = DesEncryption.Encrypt(message.Text),
                User = DesEncryption.Encrypt(message.User)
            };

            _db.Messages.Add(messageCrypt);
            await _db.SaveChangesAsync();

            await Clients.All.SendAsync("ReceiveMessage", message);
        }
    }
}
