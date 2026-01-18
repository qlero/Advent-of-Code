import System.Environment ( getArgs )

palindromeChecker :: (String, String) -> Int -> Int
palindromeChecker (x:xs, y:ys) counter
    | x == y = palindromeChecker (xs, ys) $ counter + 1
    | otherwise = counter

checker :: String -> String -> Maybe (Bool, Int)
checker fw sw
    | null fw || null sw = Nothing
    | result /= 0 = Just (True, result)
    | otherwise = Just (False, result)
  where
      tup = (fw, reverse sw)
      result = palindromeChecker tup 0

main :: IO()
main = do
    args <- getArgs
    if length args < 2 
        then print "Wrong Input"
        else print $ checker (head args) (head . tail $ args)