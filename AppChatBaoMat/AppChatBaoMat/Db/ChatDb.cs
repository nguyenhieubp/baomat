using AppChatBaoMat.Models;
using Microsoft.EntityFrameworkCore;

namespace AppChatBaoMat.Db
{
    public class ChatDb:DbContext
    {
        public ChatDb(DbContextOptions<ChatDb> options):base(options)
        {
        }

        public DbSet<Messages> Messages { get; set; }
    }
}
