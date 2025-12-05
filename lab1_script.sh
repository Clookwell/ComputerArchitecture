if [ "$1" -gt "$2" ]; then
    echo "$1 більше за $2"
    alias
else
    echo "$1 менше за$2"
    echo "розмір цього файлу ($(basename "$0")): $(stat -c%s "$0") байтів"
fi
