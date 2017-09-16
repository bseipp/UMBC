console.log(gcd(12,13));
console.log(gcd(9,3));
console.log(gcd(24, 3));

function gcd(p1, p2) {
    var gcden = 0;
    if (p2 % p1 === 0){
	gcden = p1;
    }else{
	for (var i = 1; i < p1; i++){
	    if (p1 % i === 0 && p2 % i === 0){
		gcden = i;
	    }
	}
    }
    return gcden;
)