// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.8.0 <0.9.0;

contract SecPaper {
    address public owner;
    struct PaymentInfo{uint amount; uint value;}

    mapping (address => PaymentInfo) payments;

    constructor() {
        owner = msg.sender; // Кто контракт развернул, тот им и владеет
    }

    // Payable - помечает функцию принимающей деньги. 
    // Без нее деньги вернутся обратно
    function payForItem(uint _amount) public payable {
        payments[msg.sender] = PaymentInfo(_amount, msg.value);
    }

    function withdrawAll() public {
        address payable _to = payable(owner);
        address _thisContract = address(this);
        _to.transfer(_thisContract.balance);
    }

    function currentBalance() public view returns(uint) {
        return address(this).balance;
    }

    function getPayment(address _addr) public view returns(PaymentInfo memory) {
        return payments[_addr];
    }
}