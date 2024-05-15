using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace AppChatBaoMat.Models
{
    [Table(name: "Messages")]
    public class Messages
    {
        [Key]
        public Guid MessageId { get; set; }

        
        [Column]
        public string User { get; set; } = string.Empty;


        [Column]
        public string Text { get; set; } = string.Empty;
    }
}
