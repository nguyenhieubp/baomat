using AppChatBaoMat.Db;
using Microsoft.EntityFrameworkCore;

namespace AppChatBaoMat
{
    public static class ConnectDb
    {
        public static void AddConnectDb(this IServiceCollection service, IConfiguration configuration)
        {
            service.AddDbContext<ChatDb>((options) => options.UseSqlServer(configuration.GetConnectionString("DefaultConnection")));
        }
    }
}
