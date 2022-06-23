
(*values and types*)
type date = int * int * int;

val monthNames = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
];


(*funcs from task*)

fun is_older(a: date, b: date) =
    if(#1 a) > (#1 b)
    then false
    else
    if (#1 a) = (#1 b) andalso (#2 a) > (#2 b)
    then false
    else
    if (#1 a) = (#1 b) andalso (#2 a) = (#2 b) andalso (#3 a) >= (#3 b)
    then false
    else true;

fun number_in_month(dates: date list, month: int) = 
    if null dates
    then 0
    else
        number_in_month( tl dates, month ) + 
                (if #2 (hd dates) = month then 1 else 0);

fun number_in_months(dates: date list, months: int list) = 
    if null months 
    then 0
        else number_in_month(dates, hd months) 
            + number_in_months(dates, tl months);

fun dates_in_month(dates: date list, month: int) = 
    if null dates 
    then []
    else (
        if #2 (hd dates) = month 
        then (hd dates)::dates_in_month(tl dates, month)
        else dates_in_month(tl dates, month)
    );

fun dates_in_months(dates: date list, months: int list) = 
    if null months 
    then []
    else 
    dates_in_month(dates, hd months)@dates_in_months(dates, tl months);

fun get_nth(text : string list, n : int) =
    if (null text) orelse (n <= 0)
    then ""
    else 
        if n = 1
        then hd text
        else get_nth(tl text, n-1);

fun date_to_string(a: date) = 
    get_nth(monthNames, #2 a)^ " " 
    ^ Int.toString(#3 a) ^ ", " ^ Int.toString(#1 a);

fun number_before_reaching_sum(numbers: int list, sum: int) =
  if null numbers
  then 0
  else

  if (hd numbers) < sum
  then 1 + number_before_reaching_sum(tl numbers, sum - (hd numbers))
  else 0;


fun what_month(dayOfYear: int) =  
   let
    val daysPerMonth = [31,28,31,30,31,30,31,31,30,31,30,31]
  in
    number_before_reaching_sum(daysPerMonth, dayOfYear) + 1
  end;

fun numbers_range(min: int, max: int) =
  if min <= max
  then min :: numbers_range(min + 1, max)
  else [];

fun month_range(a: int, b: int) =
  if a > b
  then []
  else numbers_range(
    what_month(a),
    what_month(b)
  );

fun oldest(dates: date list) = 
    if null dates 
    then NONE
    else
        let val tl_ans = oldest(tl dates)
        in if isSome( tl_ans ) andalso is_older( valOf( tl_ans ), hd( dates ) )
            then tl_ans 
            else SOME( hd( dates ) )
        end;

(*tests*)

fun is_older_test() =
    if is_older((2022, 2, 24), (2023, 2, 5)) <> true
    then raise Fail "Test of is_older failed at 1 case."
    else

    if is_older((2022, 2, 24), (2022, 3, 24)) <> true
    then raise Fail "Test of is_older failed at 2 case."
    else

    if is_older((2022, 2, 24), (2022, 2, 25)) <> true
    then raise Fail "Test of is_older failed at 3 case."
    else
  
    if is_older((2022, 2, 24), (2022, 2, 24)) <> false
    then raise Fail "Test of is_older failed at 4 case."
    else

    print("Test of is_older passed.");

fun number_in_month_test() = 
    if number_in_month([(2022, 2, 24), (2014, 2, 14)], 2) <> 2
    then raise Fail "Test failed at 1 case."
    else

    if number_in_month([], 1) <> 0
    then raise Fail "Test failed at 2 case."
    else

    if number_in_month([(2022, 2, 24), (2014, 4, 14)], 2) <> 1
    then raise Fail "Test failed at 3 case."
    else

    if number_in_month([(2022, 2, 24), (2014, 4, 14)], 3) <> 0
    then raise Fail "Test failed at 4 case."
    else

    print("Test of number_in_month passed.");


fun number_in_months_test() =
    if number_in_months([(2022, 2, 24), (2014, 4, 14)], [2, 4]) <> 2
    then raise Fail "Test failed at 1 case."
    else

    if number_in_months([(2022, 2, 24), (2014, 4, 14)], [3, 4]) <> 1
    then raise Fail "Test failed at 2 case."
    else

    if number_in_months([(2022, 2, 24), (2014, 4, 14)], [6, 8]) <> 0
    then raise Fail "Test failed at 2 case."
    else

    if number_in_months([], [1]) <> 0
    then raise Fail "Test failed at 3 case."
    else

    if number_in_months([(2022, 2, 24)], [1]) <> 0
    then raise Fail "Test failed at 4 case."
    else

    print("Test of number_in_months passed.");

fun dates_in_month_test() =
  if dates_in_month([(2022, 2, 24), (2014, 2, 22)], 2) <> [(2022, 2, 24), (2014, 2, 22)]
    then raise Fail "Test of dates_in_month failed at 1 case."
    else

    if dates_in_month([(2022, 2, 24), (2014, 2, 22)], 1) <> []
    then raise Fail "Test of dates_in_month failed at 2 case."
    else

    if dates_in_month([(2022, 2, 24), (2014, 4, 14)], 2) <> [(2022, 2, 24)]
    then raise Fail "Test of dates_in_month failed at 3 case."
    else

    if dates_in_month([(2022, 2, 24), (2014, 4, 14)], 4) <> [(2014, 4, 14)]
    then raise Fail "Test of dates_in_month failed at 4 case."
    else

    print("Test of dates_in_month passed.");


fun dates_in_months_test() =
    if dates_in_months([(2022, 2, 24), (2014, 4, 14)], [2, 4]) <> [(2022, 2, 24), (2014, 4, 14)]
    then raise Fail "Test of dates_in_months failed at 1 case."
    else

    if dates_in_months([(2022, 2, 24), (2014, 4, 14)], [3]) <> []
    then raise Fail "Test of dates_in_months failed at 2 case."
    else

    if dates_in_months([(2022, 2, 24), (2014, 4, 14)], [2]) <> [(2022, 2, 24)]
    then raise Fail "Test of dates_in_months failed at 3 case."
    else

    if dates_in_months([], [1]) <> []
    then raise Fail "Test of dates_in_months failed at 4 case."
    else

    print("Test of dates_in_months passed.");

fun get_nth_test() =
    if get_nth(["1", "2", "3"], 1) <> "1"
    then raise Fail "Test of get_nth failed at 1 case."
    else 

    if get_nth(["1", "2", "3"], 2) <> "2"
    then raise Fail "Test of get_nth failed at 2 case."
    else

    if get_nth(["1", "2", "3"], 4) <> ""
    then raise Fail "Test of get_nth failed at 3 case."
    else

    print("Test of get_nth passed.");

fun date_to_string_test() =
    if date_to_string((2022, 2, 24)) <> "February 24, 2022"
    then raise Fail "Test of date_to_string failed at 1 case."
    else 

    print("Test of date_to_string passed.");


fun number_before_reaching_sum_test() =
    if number_before_reaching_sum([1, 2, 3], 1) <> 0
    then raise Fail "Test of number_before_reaching_sum failed at 1 case."
    else 

    if number_before_reaching_sum([1, 2, 3], 2) <> 1
    then raise Fail "Test of number_before_reaching_sum failed at 2 case."
    else

    if number_before_reaching_sum([1, 2, 3], 3) <> 1
    then raise Fail "Test of number_before_reaching_sum failed at 3 case."
    else

    if number_before_reaching_sum([1, 2, 3], 4) <> 2
    then raise Fail "Test of number_before_reaching_sum failed at 4 case."
    else

    print("Test of number_before_reaching_sum passed.");

fun what_month_test() =
    if what_month(1) <> 1
    then raise Fail "Test of what_month failed at 1 case."
    else 

    if what_month(31) <> 1
    then raise Fail "Test of what_month failed at 2 case."
    else

    if what_month(32) <> 2
    then raise Fail "Test of what_month failed at 3 case."
    else

    if what_month(360) <> 12
    then raise Fail "Test of what_month failed at 4 case."
    else

    print("Test of what_month passed.");

fun month_range_test() =
    if month_range(2, 1) <> []
    then raise Fail "Test of month_range failed at 1 case."
    else 

    if month_range(1, 31) <> [1]
    then raise Fail "Test of month_range failed at 2 case."
    else

    if month_range(1, 32) <> [1, 2]
    then raise Fail "Test of month_range failed at 3 case."
    else

    if month_range(1, 360) <> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    then raise Fail "Test of month_range failed at 4 case."
    else

    print("Test of month_range passed.");

fun oldest_test() =
    if oldest([(2022, 2, 24), (2014, 4, 14)]) <> SOME((2014, 4, 14))
    then raise Fail "Test of oldest failed at 1 case."
    else

    if oldest([(2014, 4, 14), (2014, 4, 14)]) <> SOME((2014, 4, 14))
    then raise Fail "Test of oldest failed at 2 case."
    else

    if oldest([]) <> NONE
    then raise Fail "Test of oldest failed at 3 case."
    else
    print("Test of oldest passed.");
(*run*)

is_older_test();
number_in_month_test();
number_in_months_test();
dates_in_month_test();
dates_in_months_test();
get_nth_test();
date_to_string_test();
number_before_reaching_sum_test();
what_month_test();
month_range_test();
oldest_test();
