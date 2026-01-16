-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND year = '2024' AND month = '7' AND day = '28';
SELECT * FROM interviews WHERE transcript LIKE '%bakery%';
SELECT * FROM bakery_security_logs;
SELECT * FROM phone_calls WHERE phone_calls.year = '2024' AND phone_calls.month = '7' AND phone_calls.day = '28';
SELECT * FROM airports;
SELECT * FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city = 'Fiftyville'
AND flights.year = 2024 AND flights.month = 7 AND flights.day = 29
;

SELECT DISTINCT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE bakery_security_logs.year = '2024'
AND bakery_security_logs.month = '7' AND bakery_security_logs.day = '28' AND bakery_security_logs.hour = '10' AND bakery_security_logs.minute <= '25' AND bakery_security_logs.activity = 'exit'
AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.year = '2024' AND atm_transactions.month = '7' AND atm_transactions.day = '28' AND atm_transactions.transaction_type = 'withdraw'
AND phone_calls.year = '2024' AND phone_calls.month = '7' AND phone_calls.day = '28' AND phone_calls.duration < '60'
AND flights.year = 2024 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8
AND airports.city = 'Fiftyville'
;

SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE people.name = 'Bruce'
;
