SELECT songs.name FROM artists
JOIN songs ON artists.id = songs.artist_id
WHERE artists.name = "Post Malone";