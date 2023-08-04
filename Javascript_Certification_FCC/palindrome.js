function palindrome(str) {
    str = str.toLowerCase().replace(/[\W_]/g, '');
    return isPalindrome(str);
  }
  
  function isPalindrome(str) {
    let len = Math.floor(str.length/2);
    for (let i = 0; i < len; i++){
      if (str[i] !== str[str.length -i -1]){
        return false;
        }
      }
    return true;
  }
  
  palindrome("eye");
  