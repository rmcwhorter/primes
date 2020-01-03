#[macro_use]
extern crate timeit;

fn is_prime(n: i64) -> bool {
    if n <= 1 {
        return false;
    }
    if n <= 3 {
        return true;
    }

    if (n%2 == 0) || (n%3 == 0) {
        return false;
    }

    let mut i: i64 = 5;
    while i*i <= n {
        if (n%i == 0) || (n%(i+2) == 0) {
            return false;
        }
        i = i+6;
    }

    return true;
}

fn next_prime(n: i64) -> i64 {
    if n <= 1 {
        return 2;
    }

    let mut prime: i64 = n;
    let mut found: bool = false;

    while !found {
        prime += 1;
        if is_prime(prime) {
            found = true;
        }
    }

    return prime;
}

fn factorize(n: i64) -> Vec<i64> {
    let mut live: i64 = n;
    let mut rtn: Vec<i64> = vec![];

    let mut prime: i64 = 2;
    while (&rtn).into_iter().product::<i64>() != n {
        if live % prime == 0 {
            rtn.push(prime);
            live = live / prime;
        } else {
            prime = next_prime(prime);
        }
    }

    return rtn;
}

fn main() {
    println!("=====SOF=====\n\n");
    let int_1 = 858645989;
    let int_2 = 977666464;
    let n = 100;

    let seconds_1 = timeit_loops!(n, {
        factorize(int_1);
    });
    let seconds_2 = timeit_loops!(n, {
        factorize(int_2);
    });

    println!("{} has prime factorization\n{:?}", int_1, factorize(int_1));
    println!("{} has prime factorization\n{:?}\n", int_2, factorize(int_2));

    println!("Factoring {} took an average of {} microseconds, over {} trials.", int_1, seconds_1 * 10_f64.powf(6.0), n);
    println!("Factoring {} took an average of {} microseconds, over {} trials.", int_2, seconds_2 * 10_f64.powf(6.0), n);

    println!("\n\n=====EOF=====");
}
