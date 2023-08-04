const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const jump = 13;

function rot13(str) {
  let res = "";
  for(let i = 0; i < str.length; i++) {
    res += translator(str[i], jump);
  }
  return res;
}

function translator(l, j) {
  l = l.toUpperCase();
  return alphabet.includes(l) ? alphabet[(alphabet.indexOf(l) + j) % alphabet.length] : l;
}

rot13("SERR PBQR PNZC");