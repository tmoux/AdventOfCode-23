module Main where

import Control.Applicative ((<**>))
import Data.Either (fromRight)
import Text.Parsec
import Text.Parsec.String (Parser)

parseInt :: Parser Int
parseInt = read <$> many1 digit

parseRGB :: Parser RGB
parseRGB = chainl parseSingle (string ", " >> pure add) (RGB 0 0 0)
  where
    add (RGB a b c) (RGB x y z) = RGB (a + x) (b + y) (c + z)

parseSingle :: Parser RGB
parseSingle =
  parseInt
    <**> choice
      [ try $ string " red" >> pure (\x -> RGB x 0 0),
        try $ string " green" >> pure (\x -> RGB 0 x 0),
        try $ string " blue" >> pure (\x -> RGB 0 0 x)
      ]

parseLine :: Parser [RGB]
parseLine = string "Game " *> parseInt *> string ": " *> parseRGB `sepBy` string "; "

data RGB = RGB Int Int Int
  deriving (Show)

part1 :: [[RGB]] -> Int
part1 xs = sum $ zipWith (\i r -> (if all f r then i else 0)) [1 ..] xs
  where
    f (RGB r g b) = r <= 12 && g <= 13 && b <= 14

part2 :: [[RGB]] -> Int
part2 xs = sum $ map (prod . f) xs
  where
    f = foldr (\(RGB a b c) (RGB x y z) -> RGB (max a x) (max b y) (max c z)) (RGB 0 0 0)
    prod (RGB r g b) = r * g * b

main :: IO ()
main = do
  ls <- lines <$> getContents
  let parsed = map (fromRight (error "") . parse parseLine "") ls
  putStrLn $ "Part 1: " ++ show (part1 parsed)
  putStrLn $ "Part 2: " ++ show (part2 parsed)
