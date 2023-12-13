{-# OPTIONS_GHC -Wno-incomplete-uni-patterns #-}

module Main where

import Data.List.Split (splitOn)
import qualified Data.Set as S
import Data.Tuple.Extra (both)

-- For a pair of sets (S, T), count how many times an element in T occurs in S.
matches :: [(S.Set Int, S.Set Int)] -> [Int]
matches = map (uncurry f)
  where
    f s t = S.size (S.intersection s t)

part1 :: [Int] -> Int
part1 = sum . map (\x -> if x == 0 then 0 else 2 ^ (x - 1))

part2 :: [Int] -> Int
part2 ls = sum $ foldl (\cur _ -> cur ++ [cnt cur]) [] ls
  where
    cnt cur =
      1 + sum (zipWith countCopies cur [0 ..])
      where
        countCopies x i = if i + ls !! i >= length cur then x else 0

main :: IO ()
main = do
  ls <- lines <$> getContents
  let parsed =
        map
          ( \l ->
              let (x : y : _) = splitOn ["|"] (drop 2 (words l))
               in both (S.fromList . map read) (x, y)
          )
          ls
      ms = matches parsed
  putStrLn $ "Part 1: " ++ show (part1 ms)
  putStrLn $ "Part 2: " ++ show (part2 ms)
