use master;


DELETE from Messages where MessageId = 'd5ae3eb2-e43a-474a-5a55-08dc5bcf69d4';

use ChatDes;
Drop table Messages;
select * from Messages;

DELETE from Messages where MessageId = '0cfa1825-741d-44ac-0907-08dc5bd5d330';
CREATE TABLE Messages (
    MessageId UNIQUEIDENTIFIER PRIMARY KEY,
    [User] NVARCHAR(MAX) NOT NULL,
    Text NVARCHAR(MAX) NOT NULL
);
