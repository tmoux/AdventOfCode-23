module Main where

-- https://stackoverflow.com/questions/9512513/how-do-you-compute-the-difference-between-successive-elements-of-a-list-of-unkno
diffs :: Num a => [a] -> [a]
diffs [] = []
diffs l = zipWith (-) (tail l) l

part1 :: [[Int]] -> Int
part1 = sum . map f
  where
    f [] = 0
    f xs | all (0 ==) xs = 0
         | otherwise = last xs + f (diffs xs)

part2 :: [[Int]] -> Int
part2 = sum . map f
  where
    f [] = 0
    f xs | all (0 ==) xs = 0
         | otherwise = head xs - f (diffs xs)

main :: IO ()
main = do
  input <- map (map read . words) . lines <$> getContents
  putStrLn $ "Part 1: " ++ show (part1 input)
  putStrLn $ "Part 2: " ++ show (part2 input)