#!/bin/sh

# Create (unique) temporary directories
tar=$(mktemp -d /tmp/XXXXXXXX)
gzip=$(mktemp -d /tmp/XXXXXXXX)

# Generate 5 ascii encoded random files (to be sure tar can handle them lossless)
for i in $(seq 1 5); do
  # retrieve random number (4 digits) from /dev/urandom
  size=$( (tr -dc '0-9' | fold -w 4 | head -n 1) < /dev/urandom)
  # retrieve random data to fill files
  fileContents=$(base64 /dev/urandom | head -c "$size")
  echo "$fileContents" > "$tar/$i"
  echo "$fileContents" > "$gzip/$i"
done

echo "== Two directories with same content"
# Retrieve size of files
ls -smh "$tar" "$gzip"
# -s : sort by file size
# -m : comma separated list
# -h : human readable sizes
# Ensure files are the same
diff -s "$tar" "$gzip"
# -s : report identical files

# Create .tar
cd "$tar" || exit 2
tar -cf "$tar.tar" .
# -c : create archive
# -f : archive name

# Create .tar.gz
cd "$gzip" || exit 2
tar -czf "$gzip.tar.gz" .
# -z : filter archive through gzip(1)

echo "== Size difference after archiving"
du -h "$tar.tar"
du -h "$gzip.tar.gz"
# -h : human readable sizes

# .tar is an uncompressed archive. We can observe the same size before and after
# archiving process.

# .tar.gz is a compressed archive. It uses gzip as a compression system.
# We can read on gzip(1) that it uses Lempel-Ziv coding (LZ77) data compression
# algorithm. We can use gzip on files that are not archives, we usually name
# them *.gz files.

rm -rf "$tar"
rm -f "$tar.tar"
rm -rf "$gzip"
rm -f "$gzip.tar.gz"
