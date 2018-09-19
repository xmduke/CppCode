create database ChatSev;

CREATE TABLE `chatsev`.`userinfo` 
(
  `uId` INT NOT NULL AUTO_INCREMENT,
  `uName` VARCHAR(45) NULL,
  PRIMARY KEY (`uId`),
  UNIQUE INDEX `uId_UNIQUE` (`uId` ASC)
);

insert into 
ChatSev.userinfo(uName)
values("z1");

insert into ChatSev.userinfo(uName)values('f0ng');

select * from chatSev.userinfo;