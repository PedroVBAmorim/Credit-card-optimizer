# Credit-card-optimizer
C++ console application that helps users choose the highest‑value credit card based on their spending habits and preferences. The program models multiple cards (annual fees, sign‑up bonuses, reward rates, perks, travel partners, and foreign transaction fees) and scores each one against a user profile to recommend the best fit.
Models credit cards with:

Annual fee

Sign‑up bonus (points and point value)

Category reward rates (travel, dining, grocery, other)

Perk value per year

Number of travel partners

Foreign transaction fee rate

Collects a user profile:

Annual spend in travel, dining, grocery, and other

Fraction of spending that is foreign

Tunable weights for sign‑up bonus, ongoing rewards, perks, fees, partners, and FX fees

Computes:

Estimated dollar value of sign‑up bonus

Estimated annual rewards value from spending

Estimated yearly foreign transaction fees

A single score per card and an approximate net first‑year value

Outputs:

Recommended card name

Breakdown of sign‑up bonus value, ongoing rewards, perks, annual fee, FX fees, and net first‑year value
