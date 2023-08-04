const table = [0.01, 0.05, 0.1, 0.25, 1, 5, 10, 20, 100];

function checkCashRegister(price, cash, cid) {
  let total = cid.reduce((sum, elem) => sum + elem[1], 0).toFixed(2);
  let change = cash - price;
  if (total == change) {
    return {status: "CLOSED", change: cid};
  }
  if (change > total) {
    return {status: "INSUFFICIENT_FUNDS", change: []};
  }
  let finalChange = [ 
    ["PENNY", 0], 
    ["NICKEL", 0],
    ["DIME", 0],
    ["QUARTER", 0],
    ["ONE", 0],
    ["FIVE", 0],
    ["TEN", 0],
    ["TWENTY", 0],
    ["ONE HUNDRED", 0]
  ];
  let changeAvailable = cid.slice();
  for (let i = finalChange.length -1; i >= 0; i--) {
    while(change >= table[i] && changeAvailable[i][1] > 0){
      change -= table[i];
      change = change.toFixed(2);
      changeAvailable[i][1] -= table[i];
      finalChange[i][1] += table[i];
    }
  }
  if (change == 0) {
    return {status: "OPEN", change: finalChange.filter(val => val[1] !== 0).reverse()};
  }
  return {status: "INSUFFICIENT_FUNDS", change: []};
}

checkCashRegister(19.5, 20, [["PENNY", 1.01], ["NICKEL", 2.05], ["DIME", 3.1], ["QUARTER", 4.25], ["ONE", 90], ["FIVE", 55], ["TEN", 20], ["TWENTY", 60], ["ONE HUNDRED", 100]]);
