-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 01 Jan 2021 pada 16.56
-- Versi server: 10.4.11-MariaDB
-- Versi PHP: 7.4.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `arduino_mysql`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `arduino_data`
--

CREATE TABLE `arduino_data` (
  `id` int(6) UNSIGNED NOT NULL,
  `variabel` varchar(30) NOT NULL,
  `nilai` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `browser_data`
--

CREATE TABLE `browser_data` (
  `id` int(6) UNSIGNED NOT NULL,
  `variabel` varchar(30) NOT NULL,
  `nilai` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `browser_data`
--

INSERT INTO `browser_data` (`id`, `variabel`, `nilai`) VALUES
(1, 'FIRYAN', '100'),
(2, 'RIZKY', '90');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `arduino_data`
--
ALTER TABLE `arduino_data`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `browser_data`
--
ALTER TABLE `browser_data`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `arduino_data`
--
ALTER TABLE `arduino_data`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `browser_data`
--
ALTER TABLE `browser_data`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
