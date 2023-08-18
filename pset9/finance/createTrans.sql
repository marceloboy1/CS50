CREATE TABLE transactions (
                id INTEGER,
                userId INTEGER,
                companyName TEXT,
                symbol TEXT,
                shares INTEGER,
                price REAL,
                transacted DATETIME,
                FOREIGN KEY(userId) REFERENCES users(id)
                PRIMARY KEY (id)
            );

CREATE UNIQUE INDEX userId ON transactions(userId);

SELECT symbol, companyName, sum(shares) FROM transactions WHERE userId = 2 GROUP BY symbol;

SELECT sum(shares) as shares FROM transactions WHERE userId = 3 AND symbol = 'GOOGL';

