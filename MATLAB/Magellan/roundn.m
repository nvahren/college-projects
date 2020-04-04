% Round x to the n-th decimal place
function x = roundn(x,n)
x = x*10^n;
x = round(x);
x = x/10^n;
