const {expect} = require("chai")
const {ethers} = require("hardhat")

describe("SecPaper", function(){
    let acc1;
    let acc2;
    let sec_paper;

    beforeEach(async function(){
        [acc1, acc2] =  await ethers.getSigners();
        const SecPaper = await ethers.getContractFactory("SecPaper", acc1);
        sec_paper = await SecPaper.deploy(); // Отправляет транзакцию
        await sec_paper.deployed(); // Ждет пока она будет выполнена 
        console.log(sec_paper.address)
    })

    it("should be deployed", async function(){
        // Ожидание, что адресс контракта является корректным
        expect(sec_paper.address).to.be.properAddress;
    }) 

    it("start balance is zero", async function(){
        // Ожидание, что адресс контракта является корректным
        const balance = await sec_paper.currentBalance();
        expect(balance).to.eq(0);
    }) 

    it("payForItem is work", async function(){
        const tx = await sec_paper.payForItem(12, {value: 5});

        // Проверка, что на втором акке изменился счет
        expect(() => tx)
            .to.changeEtherBalances([acc1, acc2], [5, -5]);

        await tx.wait();
        const balance = await sec_paper.currentBalance();
        expect(balance).to.eq(5);
    }) 

    it("getPayment is work", async function(){
        const tx = await sec_paper.connect(acc2).payForItem(12, {value: 5});
        await tx.wait();
        const payment = await sec_paper.getPayment(acc2.address);
        expect(payment.amount).to.eq(12);
        expect(payment.value).to.eq(5);
    }) 


    it("withdrawAll is work", async function(){
        const tx = await sec_paper.connect(acc2).payForItem(12, {value: 5});

        expect(() => tx).to.changeEtherBalance(acc1, 5);
        await tx.wait();
        
        await sec_paper.withdrawAll();
        const balance = await sec_paper.currentBalance();
        expect(balance).to.eq(0);


    }) 
})