{-# LANGUAGE OverloadedStrings #-}

module Main where

import Control.Applicative (asum)
import Control.Monad.Writer
  ( MonadWriter (tell),
    Writer,
    execWriter,
  )
import Data.List (intercalate)
import Data.Maybe (fromJust)
import qualified Data.Text as T
import qualified Data.Text.IO as T
import Text.Printf (printf)
import Control.Arrow ((>>>))

findMatch :: [(Int, T.Text -> Maybe Int)] -> T.Text -> Maybe Int
findMatch fs txt = asum (map (\(len, f) -> f (T.take len txt)) fs)

findFirst :: [(Int, T.Text -> Maybe Int)] -> T.Text -> Maybe Int
findFirst fs txt = asum (map (findMatch fs) suffixes)
  where
    suffixes = T.tails txt

findLast :: [(Int, T.Text -> Maybe Int)] -> T.Text -> Maybe Int
findLast fs txt = findFirst fs' (T.reverse txt)
  where
    fs' = map (\(len, f) -> (len, f . T.reverse)) fs

createTest :: T.Text -> Int -> (Int, T.Text -> Maybe Int)
createTest t i = (T.length t, \s -> if s == t then Just i else Nothing)

part1Tests :: [(Int, T.Text -> Maybe Int)]
part1Tests =
  map
    (uncurry createTest)
    [ ("1", 1),
      ("2", 2),
      ("3", 3),
      ("4", 4),
      ("5", 5),
      ("6", 6),
      ("7", 7),
      ("8", 8),
      ("9", 9)
    ]

part2Tests :: [(Int, T.Text -> Maybe Int)]
part2Tests =
  part1Tests
    ++ map
      (uncurry createTest)
      [ ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9)
      ]

getNumber :: (T.Text -> Maybe Int) -> (T.Text -> Maybe Int) -> T.Text -> Maybe Int
getNumber f g txt = (\x y -> 10 * x + y) <$> f txt <*> g txt

part1 :: [T.Text] -> Int
part1 = sum . map (fromJust . getNumber (findFirst part1Tests) (findLast part1Tests))

part2 :: [T.Text] -> Int
part2 = sum . map (fromJust . getNumber (findFirst part2Tests) (findLast part2Tests))

solve :: T.Text -> Writer [String] ()
solve txt = do
  let ws = T.splitOn "\n" txt
  tell [printf "Part 1: %d" (part1 ws)]
  tell [printf "Part 2: %d" (part2 ws)]

main :: IO ()
main = T.interact solve'
  where
    solve' = solve >>> execWriter >>> (++ [""]) >>> intercalate "\n" >>> T.pack
