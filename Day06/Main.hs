module Main where

import Data.Tuple.Extra (both)

-- Count the number of integer points x where (t - x) * x > d.
getRoots :: Int -> Int -> Int
getRoots t d =
  if disc <= 0
    then 0
    else max 0 (r - l + 1)
  where
    disc :: Double
    disc = fromIntegral (t * t - 4 * d)
    l = ceil' ((fromIntegral t - sqrt disc) / 2.0)
    r = floor' ((fromIntegral t + sqrt disc) / 2.0)
    isInt x = x == fromInteger (round x)
    ceil' x = ceiling x + if isInt x then 1 else 0
    floor' x = floor x + if isInt x then -1 else 0

part1 :: [(Int, Int)] -> Int
part1 = product . map (uncurry getRoots)

part2 :: (Int, Int) -> Int
part2 = uncurry getRoots

main :: IO ()
main = do
  times <- drop 1 . words <$> getLine
  distances <- drop 1 . words <$> getLine
  let part1Input = uncurry zip (both (map read) (times, distances))
      part2Input = both (read . concat) (times, distances)
  putStrLn $ "Part 1: " ++ show (part1 part1Input)
  putStrLn $ "Part 2: " ++ show (part2 part2Input)
