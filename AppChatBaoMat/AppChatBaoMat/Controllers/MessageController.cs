using AppChatBaoMat.Db;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace AppChatBaoMat.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class MessageController : ControllerBase
    {
        private readonly ChatDb _db;

        public MessageController(ChatDb db)
        {
            _db = db;
        }

        //đúng
        [HttpGet]
        public IActionResult GetAllMessage()
        {
            var messages = _db.Messages.ToArray();

            // Giải mã User và Text trước khi trả về cho client
            foreach (var message in messages)
            {
                message.User = DesEncryption.Decrypt(message.User);
                message.Text = DesEncryption.Decrypt(message.Text);
            }

            return Ok(messages);
        }


        [HttpDelete]
        [Route("DeleteAllMessage")]
        public IActionResult DeleteMessage()
        {
            var messages = _db.Messages.ToArray();
            foreach(var message in messages)
            {
                _db.Messages.Remove(message);
            }
            _db.SaveChanges();
            return Ok("Delete Success");
        }


    }
}
