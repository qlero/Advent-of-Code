-- (<$>) :: Functor f     => (a -> b) -> f a -> f b
-- (<*>) :: Applicative f => f (a -> b) -> f a -> f b
-- (>>=) :: Monad m       => m a -> (a -> m b) -> m b

-- functors, applicatives and monads are a TYPECLASS
-- a typeclass can be thought of as an interface it defines or gives us 
-- the signatude of a method

------ class Functor f where
------     fmap :: (a -> b) -> f a -> f b
data Maybe2 a = Just2 a | Nothing2 deriving Show
instance Functor Maybe2 where
    fmap f (Just2 a)  = Just2 (f a)
    fmap f Nothing2 = Nothing2

data Tree a = Tip a | Branch (Tree a) (Tree a) deriving Show
instance Functor Tree where
    fmap f (Tip a) = Tip (f a)
    fmap f (Branch left right) = Branch (fmap f left) (fmap f right)

------ class Functor f => Applicative f where
------     pure :: a -> f a
------     (<*>) :: f (a -> b) -> f a -> f b
instance Applicative Maybe2 where
    pure = Just2
    Just2 f <*> j = fmap f j
    Nothing2 <*> j = Nothing2

instance Applicative Tree where
    pure = Tip
    Tip f <*> t = fmap f t
    Branch left right <*> t = Branch (left <*> t) (right <*> t)

-- Monads applies a function (e.g. (+3)) to a wrapped value and returns
-- a wrapped value. It's a TOILET PLUNGER.
half :: Integral a => a -> Maybe2 a
half x = if even x then Just2 (x `div` 2) else Nothing2

treeOperation :: (Eq a, Num a) => a -> Tree a
treeOperation x 
    | x == 1 = Tip 1
    | otherwise = Branch (Tip (x*2)) (Tip (x*4))

instance Monad Maybe2 where -- (>>=) bind symbol 
    Nothing2 >>= f = Nothing2
    Just2 val >>= f = f val

instance Monad Tree where
    Tip a >>= f = f a
    Branch left right >>= f = Branch (left >>= f) (right >>= f)

main :: IO()
main = do
    -------- Functors
    let tree = Branch (Tip 1) (Branch (Tip 2) (Tip 3))
    print $ (+3) 9 -- print $ fmap (+3) $ Just2 9 -- Just2 12
    print $ (+3) <$> Just2 9 -- Just2 12
    print $ fmap (+3) tree -- Branch (Tip 4) (Branch (Tip 5) (Tip 6))
    -- (*) <$> (Just 8) <*> (Just 2) -> Just 16
    -- [(*2), (+3)] <*> [1,2,3] -> [2,4,6,4,5,6]
    
    -------- Applicatives
    print $ Just2 (+3) <*> Just2 9 -- Just2 12
    print $ Tip (+1) <*> tree -- Branch (Tip 2) (Branch (Tip 3) (Tip 4))
    print $ Branch (Tip (+1)) (Tip (\x -> x-1)) <*> tree
    -- Branch ( Branch (Tip 2) (Branch (Tip 3) (Tip 4)) ) (
    --          Branch (Tip 0) (Branch (Tip 1) (Tip 2)) )

    -------- Monads
    print $ Just2 4 >>= half -- Just 2
    print $ Nothing2 >>= half -- Nothing
    print $ (>>=) . Just2 <$> [1,2,3] <*> [half] -- [Nothing,Just 1,Nothing]
    print $ tree >>= treeOperation
    -- Branch (Tip 1) 
    --        (Branch (Branch (Tip 4) (Tip 8)) (Branch (Tip 6) (Tip 12)))