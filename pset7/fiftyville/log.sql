-- Keep a log of any SQL queries you execute as you solve the mystery.
.mode list
-- checking crime description
SELECT description FROM crime_scene_reports WHERE month = 07 AND day = 28 AND year = 2020 AND street = "Chamberlin Street";
-- Time of crime 10:15am
-- Location  Chamberlin Street courthouse.
-- Three witness interview

-- checking interviews
SELECT id, name, transcript FROM interviews WHERE day = 28 AND month = 07 AND year = 2020;
-- 161 The thief drove away in a car at 10:25am
-- 162 The thief withdraw money in the ATM before 10:15
-- 163 The thief talked to the phone in less then a minute
-- He got the first flight outta town next day, ticket purchased by cumplice

-- Checking the first flight for next day
SELECT city FROM airports WHERE id =
(SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1);

SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1;
-- The suspect flew to LONDON on flight 36

-- cross all that information
-- accounts who made withdraw that day in Fifer St
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"))
INTERSECT
-- calls made in that day  shorter then 1 minute
SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60)
INTERSECT
-- cars leaving the parking lot FROM 10:15 to 1025
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND  day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity  = "exit")
INTERSECT
--passenger list for the first flight on 29/07
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- ERNEST IS THE MAIN SUSPECT

-- now we check to see who he was calling
SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Ernest"));

-- BERTHOLD IS THE ACCOMPLICE