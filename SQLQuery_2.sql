use Amazon;
select * from Stock.Transactions;
delete from Stock.Transactions WHERE TransactionId = 'f019d844-42f9-40df-c241-08dc65ffb44f'
delete from IAM.Users where UserId = '4f532ed0-1402-4abf-12b0-08dc578bbe8d'
delete from Money.Wallets where WalletId = '3fa85f64-5717-4562-b3fc-2c963f66afa6'
SELECT * from Money.Wallets;
select * from IAM.Users;

INSERT Money.Wallets(WalletId,Money,UserId) VALUES('3fa85f64-5717-4562-b3fc-2c963f66afa6',1000,'e6f60d7d-ac39-414a-12af-08dc578bbe8d')