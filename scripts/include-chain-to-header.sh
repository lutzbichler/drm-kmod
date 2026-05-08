#!/bin/sh

set -e

start=$1
target=$2

visited=$PWD/_visited_in_chain.txt
: > "$visited"

linux_dir=$3
cd "$linux_dir"

list_headers() {
	local source=$1

	awk '
	/uapi\// {
		next;
	}
	/^#include/ {
		header = $2;
		gsub(/[<>"]/, "", header);
		print header;
		next;
	}' "$source" | while read include; do
		fd -p "/$include" arch/x86 drivers include
	done
}

find_target_from() {
	local from=$1
	local target=$2

	if grep -qF "$from" "$visited"; then
		return 1;
	else
		echo "$from" >> "$visited"
	fi

	echo "(@ $from)"

	headers=$(list_headers "$from")
	for header in $headers; do
		case "$header" in
			*$target)
				echo "*-- $target"
				echo "|-- $from"
				return 0
				;;
			*)
				;;
		esac
	done

	for header in $headers; do
		if find_target_from "$header" "$target"; then
			if test "$from" != "$start"; then
				echo "|-- $from"
			fi
			return 0
		fi
	done

	return 1
}

find_target_from "$start" "$target"
echo "\`-- $start"
