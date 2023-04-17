INSERT INTO book (SELECT
	generate_series(1, 100000) AS id,
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END ||
	CASE
		WHEN random() < 0.16129032258064516
			THEN chr(48 + floor(random() * 10)::integer)
		ELSE
			CASE
				WHEN random() < 0.5
					THEN chr(97 + floor(random() * 26)::integer)
				ELSE
					chr(65 + floor(random() * 26)::integer)
			END
	END name,
	floor(random() * (2023-1800+1) + 1800)::int AS year);

INSERT INTO book_rating (id, book_id, rating) (SELECT
	generate_series(1, 1000000) AS id,
	floor(random() * 100000)::int + 1 AS book_id,
	floor(random() * 5)::int + 1 AS rating);

INSERT INTO book_order (id, book_id, total_price) (SELECT
	generate_series(1, 1000000) AS id,
	floor(random() * 100000)::int + 1 AS book_id,
	floor(random() * 30)::int + 10 AS total_price);
