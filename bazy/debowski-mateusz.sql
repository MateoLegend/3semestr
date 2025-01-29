-- baza danych
CREATE DATABASE hotel_management;

-- tworzenie uzytkownikow
CREATE USER order_user WITH PASSWORD 'haslo123';
GRANT INSERT, SELECT ON guests, rooms, reservations TO order_user;

CREATE USER stats_user WITH PASSWORD 'haslo123';
GRANT SELECT ON reservations, rooms TO stats_user;
CREATE TABLE public.guests (
    guest_id SERIAL PRIMARY KEY,
    first_name VARCHAR(100),
    last_name VARCHAR(100),
    email VARCHAR(255) UNIQUE,
    phone_number VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
-- struktura bazy danych
CREATE TABLE public.rooms (
    room_id SERIAL PRIMARY KEY,
    room_number VARCHAR(10) UNIQUE,
    room_type VARCHAR(50),
    price_per_night DECIMAL(10, 2),
    available BOOLEAN DEFAULT TRUE
);
CREATE TABLE public.reservations (
    reservation_id SERIAL PRIMARY KEY,
    guest_id INT REFERENCES public.guests(guest_id),
    room_id INT REFERENCES public.rooms(room_id),
    check_in_date DATE,
    check_out_date DATE,
    total_cost DECIMAL(10, 2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT check_dates CHECK (check_out_date > check_in_date)
);

-- schematy
CREATE VIEW views_schema.available_rooms AS
SELECT room_id, room_number, room_type, price_per_night
FROM public.rooms
WHERE available = TRUE;
CREATE VIEW views_schema.reservation_details AS
SELECT r.reservation_id, g.first_name, g.last_name, rm.room_number, r.check_in_date, r.check_out_date, r.total_cost
FROM public.reservations r
JOIN public.guests g ON r.guest_id = g.guest_id
JOIN public.rooms rm ON r.room_id = rm.room_id;

-- funkcja
CREATE FUNCTION procedures_schema.calculate_reservation_cost(
    p_room_id INT,
    p_check_in DATE,
    p_check_out DATE
) RETURNS DECIMAL AS $$
DECLARE
    p_price DECIMAL;
    p_days INT;
BEGIN
    SELECT price_per_night INTO p_price FROM public.rooms WHERE room_id = p_room_id;
    p_days := (p_check_out - p_check_in);
    RETURN p_price * p_days;
END;
$$ LANGUAGE plpgsql;

-- procedura
CREATE PROCEDURE procedures_schema.create_reservation(
    p_guest_id INT,
    p_room_id INT,
    p_check_in DATE,
    p_check_out DATE
)
LANGUAGE plpgsql AS $$
DECLARE
    p_cost DECIMAL;
BEGIN
    p_cost := procedures_schema.calculate_reservation_cost(p_room_id, p_check_in, p_check_out);

    INSERT INTO public.reservations (guest_id, room_id, check_in_date, check_out_date, total_cost)
    VALUES (p_guest_id, p_room_id, p_check_in, p_check_out, p_cost);

    UPDATE public.rooms SET available = FALSE WHERE room_id = p_room_id;
END;
$$;

-- indeksy
CREATE INDEX idx_guests_email ON public.guests(email);

CREATE INDEX idx_rooms_room_type ON public.rooms(room_type);

CREATE INDEX idx_reservations_dates ON public.reservations(check_in_date, check_out_date);

CREATE OR REPLACE FUNCTION procedures_schema.update_room_availability()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE public.rooms SET available = TRUE WHERE room_id = OLD.room_id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

-- trigger
CREATE TRIGGER trigger_update_room_availability
AFTER DELETE ON public.reservations
FOR EACH ROW EXECUTE FUNCTION procedures_schema.update_room_availability();

-- testy
INSERT INTO public.guests (first_name, last_name, email, phone_number) 
VALUES ('Jan', 'Kowalski', 'jan.kowalski@test.com', '123456789');
INSERT INTO public.rooms (room_number, room_type, price_per_night)
VALUES ('101', 'Single', 100.00);
CALL procedures_schema.create_reservation(1, 1, '2025-02-01', '2025-02-07');